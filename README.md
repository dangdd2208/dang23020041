# PLANE_MÁY BAY TRÁNH VẬT RƠI
*[UET](https://uet.vnu.edu.vn)- Assignment - Project*.

## Giới thiệu

 Họ và Tên : Đoàn Đình Đăng.

 Lớp : *K68CC - UET*.

 Mã SV : 23020041.

 Lớp học phần : *LTNC_INT 2215_50*.

 Bài Tập lớn : *Plane_MÁY BAY TRÁNH VẬT RƠI*.

 Link bài tập lớn : https://github.com/dangdd2208/dang23020041.


## MÔ TẢ

 Đây là trò chơi theo ý tưởng của game của google khi mất mạng.

 Đây là phiên bản cho PC.
 
 Code có hơi khó đọc. Mong thầy và mọi người thông cảm ạ.

 Có âm thanh khi trải nghiệm.

 Game có các chức năng như : menu , chơi lại , mạng chơi , lưu điểm cao nhất.

## Video Demo
(Đặt liên kết video demo ở đây)

## MỤC LỤC
 1. [ Cách cài đặt game](#1-cách-cài-đặt-game)

 2. [ Cách chơi game và preview](#2-cách-chơi-game-và-preview)

 3. [ Các kĩ thuật được sử dụng](#3-các-kĩ-thuật-được-sử-dụng)

 4. [ Nguồn tham khảo](#4-nguồn-tham-khảo)

## NỘI DUNG

### 1. Cách cài đặt game
- #### 1.1 Cách tải không dùng code
   - Tải game nén thành file zip : https://github.com/dangdd2208/dang23020041/releases
   - Tải file `dowload game` để dowload game sau để giải nén tệp tin.
   - Nhấn vào tệp `Gamedemo.exe` để chơi game.
- #### 1.2 Cách tải game dùng code và có thể biên dịch  

Đầu tiên, bạn phải cài đặt [`CODE::BLOCKS`](https://www.codeblocks.org/downloads/) để chạy [C++](https://vi.wikipedia.org/wiki/C%2B%2B) và dùng cả thư viện [SDL2](https://www.libsdl.org/download-2.0.php). Tiếp theo đó là cặt đặt thêm :

- SDL 2.0: https://www.libsdl.org/download-1.2.php

- SDL_image: https://github.com/libsdl-org/SDL_image/releases

- SDL_mixer: https://github.com/libsdl-org/SDL_mixer/releases

- SDL_ttf: https://github.com/libsdl-org/SDL_ttf/releases

- Sau đó cài đặt theo hướng dẫn: https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php

Sau khi tải xong, sử dụng terminal để dowload source code(dùng lệnh `git clone`): https://github.com/dangdd2208/dang23020041.

Sau đó, bạn có thể bắt đầu trò chơi.

Mọi khó khăn liên hệ: dinhdang2208@gmail.com.

### 2. Cách chơi game và preview
Cách chơi:
- Sử dụng phím: `D` hoặc  `→`  Để di chuyển sang phải.
- Sử dụng phím: `A` hoặc `←` Để di chuyển sang trái.
- Sử dụng phím: `W` hoặc `↑` Để di chuyển lên trên.
- Sử dụng phím: `S` hoặc `↓` Để di chuyển xuống dưới.
- Khi vào game nhấn `Play`.
- Việc của người chơi là sử dụng linh hoạt các phím đúng với chức năng bên trên để điều khiển nhân vật ![logo](https://i.imgur.com/HEGmMHL.png) tránh ra khỏi các vật thể rơi ![logo](https://i.imgur.com/LeDdgGh.png) và đạt số điểm cao.Độ kho của game tăng dần theo thời gian và có cả các vật thể to hơn xuất hiện. Và bạn có một số mạng nhất định(3 mạng ![logo](https://i.imgur.com/0rAsPss.png)) khi hết mạng bạn mà chạm vào thiên thạch rơi thì sẽ GAME OVER!!!
- Khi va chạm  với thiên thạch mọi thứ sẽ chậm lại để bạn tránh đi xa khỏi thiên thạch.
- Sau khi chết có thể nhấn vào `PlayAgain` để chơi lại hoặc `Quit` để thoát. Và ở màn hình khi chết bạn có thể xem `SCORE` Và `HIGH SCORE`.
 
Preview:
- ![logo](https://i.imgur.com/AhbAStB.png)
- ![logo](https://i.imgur.com/6eoYxGD.png)
- ![logo](https://i.imgur.com/IttGDfd.png)
- ![logo](https://i.imgur.com/g5NOplS.png)
### 3. Các kĩ thuật được sử dụng

Thư viện SDL2(*hình ảnh, âm thanh, font chữ*).

Tạo  ra nhiều đối tượng : *nhân vật chính, vật thể rơi, menu*...

Sử dụng các cách tách file:
 - main.h lưu trữ các biến toàn cục của chương trình.
 - main.cpp nơi viết logic game và các hàm quan trong:
   
       - resetGame
   
       - randomDouble : sinh ra các số double ngẫu nhiên (tốc đọ cho thiên thạch )

       - Hàm check va chạm (nơi kiểm tra va chạm giữa nhân vật và thiên thạch).

       - .....
    
 - LTexture.h và LTexture.cpp là nơi tạo `class` và định nghĩa `class`.

Dùng các kiến thức lập trình cơ bản vào logic game để nhân vật chính có thể tránh được các vật thể rơi và  nâng cao số điểm.

Có thể chơi lại game vì có sử dụng các hàm *resetGame*.

Có hàm xử lí *âm thanh, Hình ảnh, Bàn phím*,....

Có sử dụng các thuật toán đơn giản.

### 4. Nguồn tham khảo

- Hình ảnh và âm  thanh , phông chữ bạn đều được tìm kiếm trên `google`.

- Tài liệu hướng dẫn của thư viện `SDL2`: https://wiki.libsdl.org

- Lazyfoo: https://lazyfoo.net/tutorials/SDL

## ĐÓNG GÓP

Cảm ơn các thầy đã hỗ trợ em:

- Thầy Lê Đức Trọng.

- Thầy Trần Trường Thủy.

- Anh Mentor:Nguyễn Bá Thanh Tùng.

## KẾT LUẬN

 Việc hoàn thiện project này giúp em mở mang rất nhiều :

- Biết cách dùng `github`.

- Biết chia nhỏ vấn đề và chia file.

- Biết cách sử dụng thư viện `SDL2`.

- Học thêm được các thuật toán.

- Biết thêm về lập trình hướng đối tượng `OOP` và `class`.
