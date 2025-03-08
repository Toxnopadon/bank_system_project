#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// ฟังก์ชันที่ประกาศใช้
void singUp();         // รับข้อมูลผู้ใช้ (สร้างบัญชี)
void pass();           // ตรวจสอบรหัสผ่าน (สร้างบัญชี)
void showData();       // แสดงข้อมูลผู้ใช้ (สร้างบัญชี)
void saveToFile();     // บันทึกข้อมูลผู้ใช้ลงไฟล์ (สร้างบัญชี)
int checkList();       // ตรวจสอบบัญชีที่มีอยู่ (สร้างบัญชี)
int checkLogin();      // ตรวจสอบข้อมูลล็อกอิน (ล็อกอิน)
void login();         // ทำการล็อกอิน (ล็อกอิน)
void showData2(char *name, int cash);// โชว์จำนวนเงินเเละชื่อของuser(ล็อกอิน)
void Listmenu(); //เลือกเมนูหลังจากทำการเข้าสู่ระบบสำเร็จ(สร้างบัญชี, ล็อกอิน)
int withdraw();//ถอนเงิน
int Deposit();//ฝากเงิน
void total();// เเสดงผลลัพธิ์ทั้งฝากเเละถอน


char name[30];           // ชื่อผู้ใช้
char password[7], password2[7]; // รหัสผ่านและการยืนยันรหัสผ่าน
int cash;

int main() {
    int service; // ตัวแปรสำหรับเลือกบริการ
    do{
    system("cls");
     printf("Create Account (1)        ");
    printf("Login (2)        ");
    printf("Out program (Other)\n");
    printf("___________________________________________________________________\n");
    printf("\nInput service number: ");
    scanf("%d", &service); // รับหมายเลขบริการจากผู้ใช้

    switch (service) {
        case 1:
            system("cls"); // ล้างหน้าจอ
            printf("              Create Account\n");
            singUp(); // เรียกฟังก์ชันลงทะเบียน
            pass(); // เรียกฟังก์ชันตรวจสอบรหัสผ่าน
            break;
        case 2:
            system("cls"); // ล้างหน้าจอ
            printf("              Login\n");
            login(); // เรียกฟังก์ชันล็อกอิน
            break;
        default:
            system("cls");
            printf("\n\n\n");
            printf("**********Thank you for using the service.**********");// แสดงข้อความขอบคุณ
            printf("\n\n\n");
            exit(1);
            }
            }
         while (service != 0) ;
          Sleep(2000);
    return 0; // ส่งค่ากลับจากฟังก์ชัน main
}

// ฟังก์ชันสำหรับการลงทะเบียนผู้ใช้
void singUp() {
    printf("______________________________________________\n\n");
    printf("Input your name (30 characters max): ");
    scanf("%s", name); // รับชื่อผู้ใช้

    // ตรวจสอบความยาวของชื่อ
    if (strlen(name) > 30) {
        printf("Name is too long, please use 30 characters max.\n");
        exit(1); // หยุดโปรแกรมถ้าชื่อเกินความยาวที่กำหนด
    }

    if (checkList()) { // ตรวจสอบบัญชีที่มีอยู่
        printf("\n**********Duplicate account found.**********\n"); // แสดงข้อความหากมีบัญชีซ้ำ
        exit(1); // หยุดโปรแกรม
    }

    printf("Input your password (6 characters max): ");
    scanf("%s", password); // รับรหัสผ่าน
    // ตรวจสอบความยาวของรหัสผ่าน
    if (strlen(password) > 6) {
        printf("Password is too long, please use 6 characters max.\n");
        exit(1); // หยุดโปรแกรมถ้ารหัสผ่านเกินความยาวที่กำหนด
    }

    printf("Input your password again: ");
    scanf("%s", password2); // รับการยืนยันรหัสผ่าน
}

// ฟังก์ชันตรวจสอบรหัสผ่าน
void pass() {
    if (strcmp(password, password2) == 0) { // เปรียบเทียบรหัสผ่าน
        printf("Passwords match.\n");
        saveToFile(); // บันทึกข้อมูลลงไฟล์
        showData(); // แสดงข้อมูลผู้ใช้
    } else {
        printf("Passwords do not match.\n"); // แสดงข้อความหากรหัสผ่านไม่ตรงกัน
        exit(1); // หยุดโปรแกรมหากรหัสผ่านไม่ตรง
    }
}

// ฟังก์ชันแสดงข้อมูลผู้ใช้
void showData() {
    system("cls"); // ล้างหน้าจอ
    printf("_______________________________\n");
    printf("Name: %s\n", name); // แสดงชื่อผู้ใช้
    printf("Password: %s\n", password); // แสดงรหัสผ่าน
    printf("_______________________________\n\n");
    Sleep(2000);
    printf("Data saved successfully.\n"); // แสดงข้อความว่าข้อมูลถูกบันทึก
    Sleep(2000);
    system("cls");
    Listmenu();
}

// ฟังก์ชันบันทึกข้อมูลลงไฟล์
void saveToFile() {
    FILE *file = fopen("C:\\Users\\Admin\\OneDrive\\Desktop\\bank_system_project\\data\\DataUser.txt", "a"); // เปิดไฟล์ในโหมด append
    if (file == NULL) {
        printf("Error: Cannot open file for writing.\n"); // แสดงข้อความหากไม่สามารถเปิดไฟล์ได้
        exit(1); // หยุดโปรแกรม
    }
    fprintf(file, "Name: %s\nPassword: %s\nCash: %d\n", name, password, cash); // บันทึกข้อมูลผู้ใช้ลงไฟล์
    fclose(file); // ปิดไฟล์
}

// ฟังก์ชันตรวจสอบบัญชีที่มีอยู่
int checkList() {
    FILE *file = fopen("C:\\Users\\Admin\\OneDrive\\Desktop\\bank_system_project\\data\\DataUser.txt", "r"); // เปิดไฟล์ในโหมดอ่าน
    char nameCheck[30]; // ตัวแปรสำหรับตรวจสอบชื่อผู้ใช้
    if (file == NULL) {
        return 0; // ถ้าไฟล์ไม่พบ คืนค่า 0 หมายถึงไม่มีบัญชีซ้ำ
    }
    while (fscanf(file, "Name: %s\nPassword: %s\nCash: %d\n", nameCheck, password, &cash) != EOF) { // อ่านข้อมูลจากไฟล์
        if (strcmp(name, nameCheck) == 0) { // เปรียบเทียบชื่อผู้ใช้
            fclose(file); // ปิดไฟล์
            return 1; // พบบัญชีซ้ำ
        }
    }
    fclose(file); // ปิดไฟล์
    return 0; // ไม่มีบัญชีซ้ำ
}

int checkLogin(char *name, char *password) {
    char nameCheck[30]; // ตัวแปรสำหรับตรวจสอบชื่อผู้ใช้
    char passwordCheck[7]; // ตัวแปรสำหรับตรวจสอบรหัสผ่าน
    int cashCheck; // ตัวแปรสำหรับตรวจสอบจำนวนเงิน
    FILE *file = fopen("C:\\Users\\Admin\\OneDrive\\Desktop\\bank_system_project\\data\\DataUser.txt", "r"); // เปิดไฟล์ในโหมดอ่าน

    // ตรวจสอบว่าเปิดไฟล์ได้หรือไม่
    if (file == NULL) {
        printf("Error: Cannot open file for reading.\n"); // แสดงข้อความหากไม่สามารถเปิดไฟล์ได้
        exit(1); // หยุดโปรแกรม
    }

    // อ่านข้อมูลจากไฟล์
    while (fscanf(file, "Name: %s\nPassword: %s\nCash: %d\n", nameCheck, passwordCheck, &cashCheck) != EOF){
        if (strcmp(name, nameCheck) == 0) { // เปรียบเทียบชื่อผู้ใช้
            if (strcmp(password, passwordCheck) == 0) { // เปรียบเทียบรหัสผ่าน
                fclose(file); // ปิดไฟล์
                cash = cashCheck; //ส่งข้อมูลเงิน
                return 0; // ล็อกอินสำเร็จ
            } else {
                fclose(file); // ปิดไฟล์
                return 2; // รหัสผ่านไม่ถูกต้อง
            }
        }
    }
    fclose(file); // ปิดไฟล์
    return 1; // ไม่พบชื่อผู้ใช้
}

// ฟังก์ชันทำการล็อกอิน
void login() {
    printf("_______________________________\n\n");
    printf("Username : ");
    scanf("%s", name); // รับชื่อผู้ใช้
    printf("Password : ");
    scanf("%s", password); // รับรหัสผ่าน

    int loginResult = checkLogin(name, password); // ส่งชื่อผู้ใช้และรหัสผ่านไปตรวจสอบ

    // ผลลัพธ์การล็อกอิน
    switch (loginResult) {
        case 0:
            printf("Login successful.\n"); // ล็อกอินสำเร็จ
            showData2(name,cash);
            break;
        case 1:
            printf("Username not found.\n"); // ไม่พบชื่อผู้ใช้
            break;
        case 2:
            printf("Incorrect password.\n"); // รหัสผ่านไม่ถูกต้อง
            break;
        default:
            printf("Unknown error occurred.\n"); // เกิดข้อผิดพลาดที่ไม่รู้จัก
    }
    system("cls");
}

// ฟังก์ชันแสดงข้อมูลผู้ใช้หลังล็อกอิน
void showData2(char *name, int cash) {
    system("cls"); // ล้างหน้าจอ
    printf("_______________________________\n\n");
    printf("Name: %s\n", name); // แสดงชื่อผู้ใช้
    printf("Cash: %d\n", cash); // แสดงจำนวนเงิน
    printf("_______________________________\n\n");
    Listmenu();
}

void Listmenu(){
    printf("withdraw (1)          Deposit (2)          out (other)\n");
    printf("___________________________________________________________________\n\n");
    printf("Select Menu : ");
    int service1; // ตัวแปรสำหรับเลือกบริการ
    scanf("%d", &service1); // รับหมายเลขบริการจากผู้ใช้

    switch (service1) {
        case 1:
           system("cls");
           printf("        withdraw\n");
           printf("______________________\n");
           withdraw();
           system("cls");
           break;
        case 2:
           system("cls");
           printf("        Deposit\n");
           printf("______________________\n");
           Deposit();
           break;
        default:
            system("cls");
            printf("name : %s\n",name);
            printf("cash : %d",cash);
             printf("\n\n\n");
            printf("**********Thank you for using the service.**********");
            printf("\n\n\n");
            exit(1);
    }
    total(cash);
}

int withdraw() {
    int withdraw;
    printf("your cash : %d\n", cash);
    printf("withdraw : ");
    scanf("%d", &withdraw);
    if (withdraw > cash) {
        printf("Insufficient funds.\n");
    } else {
        cash -= withdraw;  // หักเงิน
    }
    return cash;
}

int Deposit() {
    int Deposit;
    printf("your cash : %d\n", cash);
    printf("Deposit : ");
    scanf("%d", &Deposit);
    cash += Deposit;  // เพิ่มเงิน
    return cash;
}


void total(int cash) {
    FILE *file;
    FILE *tempFile;
    char nameCheck[30]; // ตัวแปรสำหรับตรวจสอบชื่อผู้ใช้
    char passwordCheck[7]; // ตัวแปรสำหรับตรวจสอบรหัสผ่าน
    int cashCheck; // ตัวแปรสำหรับตรวจสอบจำนวนเงิน

    // เปิดไฟล์หลักสำหรับอ่าน
    file = fopen("C:\\Users\\Admin\\OneDrive\\Desktop\\bank_system_project\\data\\DataUser.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file for reading\n");
        return; // ออกจากฟังก์ชันถ้าไม่สามารถเปิดไฟล์ได้
    }

    // สร้างไฟล์ชั่วคราวเพื่อเก็บข้อมูลที่อัปเดต
    tempFile = fopen("C:\\Users\\Admin\\OneDrive\\Desktop\\bank_system_project\\data\\temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Could not create temporary file\n");
        fclose(file); // ปิดไฟล์หลักก่อน
        return; // ออกจากฟังก์ชันถ้าไม่สามารถเปิดไฟล์ได้
    }

    // อ่านข้อมูลจากไฟล์หลักและเขียนลงในไฟล์ชั่วคราว
    while (fscanf(file, "Name: %s\nPassword: %s\nCash: %d\n", nameCheck, passwordCheck, &cashCheck) != EOF) {
        // เปลี่ยนยอดเงิน (cash) ในไฟล์ให้เป็นยอดเงินใหม่
        if (strcmp(nameCheck, name) == 0) { // เช็คชื่อผู้ใช้
            cashCheck = cash; // อัปเดตยอดเงิน
        }
        // เขียนข้อมูลลงไฟล์ชั่วคราว
        fprintf(tempFile, "Name: %s\nPassword: %s\nCash: %d\n", nameCheck, passwordCheck, cashCheck);
    }

    fclose(file); // ปิดไฟล์หลัก
    fclose(tempFile); // ปิดไฟล์ชั่วคราว

    // เปลี่ยนชื่อไฟล์ชั่วคราวให้เป็นไฟล์หลัก
    remove("C:\\Users\\Admin\\OneDrive\\Desktop\\bank_system_project\\data\\DataUser.txt"); // ลบไฟล์เก่า
    rename("C:\\Users\\Admin\\OneDrive\\Desktop\\bank_system_project\\data\\temp.txt", "C:\\Users\\Admin\\OneDrive\\Desktop\\bank_system_project\\data\\DataUser.txt"); // เปลี่ยนชื่อไฟล์ชั่วคราว

    printf("Your total cash: %d\n", cash);  // แสดงยอดเงินคงเหลือ
    Sleep(2000);
    system("cls");
    Listmenu();  // กลับไปที่เมนู
}
