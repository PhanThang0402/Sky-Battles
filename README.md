# # Dự án cuối kì lớp học phần INT2215 1 - Lập trình nâng cao
## Phan Mạnh Thắng - 21020405
### 1.Hướng dẫn cài đặt
- Lưu ý: sử dụng file project của Visual studio 2019.
- Tải project [ tại đây ](https://github.com/PhanThang0402/Sky-Battles/archive/refs/heads/main.zip)
- Giải nén file vừa tải
- Chạy chương trình:
    + Cách 1: Ấn đúp chuột vào file SkyBattles.exe trong thư mục Debug.
    + Cách 2: 
        + Truy cập vào file SkyBattles.sln bằng Visual Studio 2019.
        + Cài Solution Platforms x86 
        + Start Debugging (F5) để chạy.

### 2.Mô tả chung về trò chơi, các ý tưởng chính
#### a) Mô tả chung về trò chơi:
- Tên trò chơi: Sky Battles.
- Cách chơi :
    + Điều khiển máy bay bằng các phim mũi tên di chuyển né tránh quái vật, đạn đạo.
    + Sử dụng chuột trái/phải để bắn đạn tiêu diệt quái vật (2 loại đạn).
    + Nếu va chạm với quái vật hoặc đạn thì máy bay nổ, trò chơi kết thúc.

### b) Các ý tưởng chính:
- Hệ thống các đối tượng: main, quái vật(3 con), đạn đạo.
- Hệ thống âm thanh.
- Đồ họa bắt mắt.

### 3. Các chức năng được cài đặt trong trò chơi.
- Hiệu ứng âm thanh: click chuột bắn đạn, bắn trúng quái vật, trúng đạn quái vật, nhạc nền.
- Các chức năng chơi, menu, tương tác với chuột.
- Hiển thị thời gian chơi, điểm số (giết 1 quái = 1 điểm).
- Video demo [tại đây](https://youtu.be/uROIj4nNHuY)

### 4. Các kỹ thuật lập trình được sử dụng trong chương trình. 
- Kỹ thuật lập trình đồ họa, âm thanh bằng SDL
- Kỹ thuật lập trình hướng đối tượng.
- Kỹ thuật tách file.
- Con trỏ, mảng, cấu trúc, lớp, sinh số ngẫu nhiên.
- Xử lý va chạm,vụ nổ,...

### 5. Kết luận, hướng phát triển và các điều tâm đắc rút ra được sau khi hoàn thiện chương trình. 
#### a) Điều tâm đăc:
- Học được các kiến thức về đồ họa, SDL, biết và hiểu cơ bản cách tạo ra 1 trò chơi 2D.
- Củng cố kiến thức C++.

#### b) Hướng phát triển:
- Thêm quái vật, thay đổi quỹ đạo đạn.
- Thêm bảng xếp hạng.
- Thêm nhiều loại máy bay để lựa chọn.
- Dừng màn hình, thêm boss.

### 6. Các nguồn tài liệu tham khảo
- Các câu lệnh trong SDL:      

    + https://www.libsdl.org/
    + https://www.stdio.vn/search?
- Âm thanh game: https://freesound.org/
- Hình ảnh (open source) :
    + https://www.pngwing.com/
    + https://itch.io/

- https://phattrienphanmem123az.com/