#include <iostream>
#include <windows.h>
using namespace std;


int main() 
{
    const char* filePath = "D:/1 Hoctap/Hdh/Code/text.txt"; // Tên tệp tin

    // Mở tệp tin để đọc và ghi
    HANDLE fileHandle = CreateFileA(filePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // Mở hoặc tạo một tệp tin cho việc đọc và ghi dữ liệu.
    
    if (fileHandle == INVALID_HANDLE_VALUE) // Nếu mở tệp tin thất bại
    {
        cerr<<"Khong the mo tep tin."<<endl; //Thông báo lỗi
        return 1; //Kết thúc chương trình
    }

    // Đọc dữ liệu từ tệp tin và hiển thị nó trên màn hình
    const int bufferSize = 4096; // Kích thước buffer(bộ đệm) đọc/ghi

    char buffer[bufferSize]; // Khai bảo 1 mảng ký tự dùng để lưu trữ dữ liệu đọc từ tệp tin

    DWORD bytesRead; // Biến để lưu trữ số lượng byte đã đọc từ tệp tin trong mỗi lần đọc

    while (ReadFile(fileHandle, buffer, bufferSize, &bytesRead, NULL) && bytesRead > 0) // Đọc file từ fileHandle
    {
        cout.write(buffer, bytesRead); // Xuất dữ liệu
    }

    cout<<"\nBan co muon ghi du lieu moi vao file khong? Y/N\n"; // Có nhập dữ liệu mới không
    char check; // Khai báo biến kiểm tra
    cin>>check; // Nhập biến kiểm tra
    if (toupper(check) == 'Y') // Nếu biến kiểm tra = YES, thực hiện nhập dữ liệu 
    {
        // Nhập dữ liệu từ bàn phím và ghi vào cuối tệp tin
        cout<<"Nhap du lieu moi (nhan Enter de ket thuc):\n"; // Yêu cầu nhập dữ liệu 

        string input; // Khai báo biến lưu dữ liệu được nhập 

        cin.ignore(); // Xóa ký tự đầu tiên trong bộ nhớ đệm

        while (getline(cin, input) && !input.empty())  //Nhập dữ liệu và kiểm tra dữ liệu có rỗng hay không
        {
            DWORD bytesWritten; // Lưu số lượng byte được ghi vào tệp sau mỗi lần ghi

            if (!WriteFile(fileHandle, input.c_str(), input.size(), &bytesWritten, NULL)) // Ghi dữ liệu từ input vào tệp tin fileHandle
            {
                cerr<<"Loi khi ghi vao tep tin."<<endl; // Thông báo lỗi

                CloseHandle(fileHandle); // Đóng handle của tệp tin

                return 1; // Kết thúc chương trình
            }
        }

        // Đóng tệp tin sau khi ghi xong
        FlushFileBuffers(fileHandle); // Đảm bảo toàn bộ dữ liệu nằm trong bộ đệm đã được đẩy từ bộ đệm vào tệp tin thực sự

        CloseHandle(fileHandle); // Đóng handle, giải phóng tài nguyên 

        cout<<"Ghi du lieu moi thanh cong."<<endl; // Thông báo ghi dữ liệu thành công 
    }
    else if (toupper(check) == 'N') // Nếu biến kiểm tra = N, thông báo kết thúc
        cout<<"Chuong trinh ket thuc."; // Thông báo kết thúc chương trình

    return 0;
}