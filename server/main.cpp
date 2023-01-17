#include <iostream>
#include <fstream>
#include "Server.h"

int main() {
	char myString[] = "POST / HTTP / 1.1\r\n\
Host : 127.0.0.1 : 5000\r\n\
Connection : keep - alive\r\n\
Content - Length : 6\r\n\
sec - ch - ua : \"Not?A_Brand\"; v = \"8\", \"Chromium\"; v = \"108\", \"Google Chrome\"; v = \"108\"\r\n\
sec - ch - ua - platform: \"Windows\"\r\n\
sec - ch - ua - mobile : ? 0\r\n\
User - Agent : Mozilla / 5.0 (Windows NT 10.0; Win64; x64) AppleWebKit / 537.36 (KHTML, like Gecko) Chrome / 108.0.0.0 Safari / 537.36\r\n\
Content - Type : text / plain; charset = UTF - 8\r\n\
Accept: */*\r\n\
Origin: null\r\n\
Sec-Fetch-Site: cross-site\r\n\
Sec-Fetch-Mode: cors\r\n\
Sec-Fetch-Dest: empty\r\n\
Accept-Encoding: gzip, deflate, br\r\n\
Accept-Language: ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7\r\n\
\r\n\
chrome";
	
	std::cout << strtok_s(myString, " /", NULL) << "\n";
	std::cout << myString << "\n";

	// 1. HTTP인지 확인
	// 2. POST 요청인지 확인
	// 3. 바디 내용 확인하기
	// 4. 바디 내용이 정상적이라면 테이블에서ㅏ 찾기
	// 5. 테이블에 있으면 바로가기 실행완료
	// 6. 소켓 종료
}



	//Connection Request : 127.0.0.1 : 8701
	//Connection Request : 127.0.0.1 : 8702

	//GET / HTTP / 1.1
	//Host : 127.0.0.1 : 5000
	//Connection : keep - alive
	//sec - ch - ua : "Not?A_Brand"; v = "8", "Chromium"; v = "108", "Google Chrome"; v = "108"
	//sec - ch - ua - mobile: ? 0
	//sec - ch - ua - platform : "Windows"
	//Upgrade - Insecure - Requests : 1
	//User - Agent : Mozilla / 5.0 (Windows NT 10.0; Win64; x64) AppleWebKit / 537.36 (KHTML, like Gecko) Chrome / 108.0.0.0 Safari / 537.36
	//Accept : text / html, application / xhtml + xml, application / xml; q = 0.9, image / avif, image / webp, image / apng, */*;q=0.8,application/signed-exchange;v=b3;q=0.9
	//Sec-Fetch-Site: none
	//Sec-Fetch-Mode: navigate
	//Sec-Fetch-User: ?1
	//Sec-Fetch-Dest: document
	//Accept-Encoding: gzip, deflate, br
	//Accept-Language: ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7
