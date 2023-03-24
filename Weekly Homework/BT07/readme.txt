Câu 1:
char c = 'A', d = 'B';
char* p1 = &c;
char* p2 = &d;
char* p3;

Giả sử địa chỉ của c là 0x1234, địa chỉ của d là 0x5678. Hỏi output của đoạn lệnh sau là gì?

p3 = &d;
cout << "*p3 = " << *p3 << " , p3 = " << p3 << endl; // *p3 = B , p3 = 0x5678
p3 = p1;
cout << "*p3 = " << *p3 << " , p3 = " << p3 << endl; // *p3 = A , p3 = 0x1234
*p1 = *p2;
cout << "*p1 = " << *p1 << " , p1 = " << p1 << endl; // *p1 = B , p1 = 0x1234

Câu 2:
int *p;
int i;
int k;
i = 4;
k = i;
p = &i;

(Những) lệnh nào trong số các lệnh dưới đây sẽ gán cho i giá trị 5?
k = 5; (Sai vì gán k không ảnh hưởng đến i)
*k = 5; (Sai vì k không phải con trỏ)
p = 5; (Sai vì không thể gán con trỏ bằng một số)
*p = 5; (Đúng)

Câu 3:
char c = 'C';
double *p = &c;
Sai vì khác kiểu dữ liệu
