#include "shell.h"  // <--- ตรวจสอบให้ชัวร์ว่ามีบรรทัดนี้อยู่บนสุดครับ

int main(int argc, char* argv[]) {
    // ปิด Warning เรื่องไม่ได้ใช้ตัวแปร argc, argv (ทางเลือกเพื่อความสะอาดของ Log)
    (void)argc;
    (void)argv;

    init_shell();
    shell_loop();
    return 0;
}