#include "executor.h"
#include "builtin.h"
#include <fcntl.h>
#include <unistd.h>    // เพิ่มอันนี้: สำหรับ fork, execvp, pipe, dup2, close
#include <sys/wait.h>  // เพิ่มอันนี้: สำหรับ wait, waitpid
#include <iostream>    // เพิ่มอันนี้: สำหรับ std::cerr, std::endl

// ... โค้ดส่วนที่เหลือของคุณเหมือนเดิมได้เลยครับ ...

int execute_command(const Command& cmd) {
    if (cmd.args.empty()) return 0;

    // เช็คและทำงานแบบ Builtin ก่อน (Phase 3)
    if (is_builtin(cmd.args[0])) {
        return execute_builtin(cmd);
    }

    // แปลง std::vector<std::string> เป็น char* argv[] สำหรับ execvp (Phase 5)
    std::vector<char*> argv;
    for (const auto& arg : cmd.args) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }
    argv.push_back(nullptr);

    // Phase 2: fork() -> execvp() -> waitpid()
    pid_t pid = fork();
    if (pid == 0) {
        // --- ส่วนของ Child Process ---
        // (ระบบ Linux จะทำ Phase 4: PATH Search ค้นหาไฟล์ executable ให้โดยอัตโนมัติผ่าน execvp)
        if (execvp(argv[0], argv.data()) == -1) {
            std::cerr << "zhshell: command not found: " << argv[0] << std::endl;
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        std::cerr << "zhshell: failed to fork process" << std::endl;
        return -1;
    } else {
        // --- ส่วนของ Parent Process ---
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
    }
    return 0;
}

int execute_pipeline(const Pipeline& pipeline) {
    // Phase 9 & 10: Multi-pipe handler
    // หากมีคำสั่งเดียว รันปกติ
    if (pipeline.commands.size() == 1) {
        return execute_command(pipeline.commands[0]);
    }

    // รองรับโครงสร้าง Pipe หลายตัว
    size_t num_cmds = pipeline.commands.size();
    int pipefds[2 * (num_cmds - 1)];

    for (size_t i = 0; i < num_cmds - 1; i++) {
        if (pipe(pipefds + i * 2) < 0) {
            std::cerr << "zhshell: pipe creation failed" << std::endl;
            return -1;
        }
    }

    for (size_t i = 0; i < num_cmds; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // ถ้าไม่ใช่อันแรก: ให้รับ stdin มาจาก pipe ตัวก่อนหน้า
            if (i != 0) {
                dup2(pipefds[(i - 1) * 2], 0);
            }
            // ถ้าไม่ใช่อันสุดท้าย: ให้ส่ง stdout ไปยัง pipe ตัวถัดไป
            if (i != num_cmds - 1) {
                dup2(pipefds[i * 2 + 1], 1);
            }

            // ปิด fd ของ pipe ทั้งหมดใน child
            for (size_t j = 0; j < 2 * (num_cmds - 1); j++) {
                close(pipefds[j]);
            }

            // แปลงอาร์กิวเมนต์แล้ว exec
            std::vector<char*> argv;
            for (const auto& arg : pipeline.commands[i].args) {
                argv.push_back(const_cast<char*>(arg.c_str()));
            }
            argv.push_back(nullptr);

            if (execvp(argv[0], argv.data()) == -1) {
                std::cerr << "zhshell: exec failed" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }

    // ปิด fd ทั้งหมดใน parent
    for (size_t i = 0; i < 2 * (num_cmds - 1); i++) {
        close(pipefds[i]);
    }

    // รอเก็บศพลูกทุกตัว (wait for all children)
    for (size_t i = 0; i < num_cmds; i++) {
        wait(nullptr);
    }

    return 0;
}