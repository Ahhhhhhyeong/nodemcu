#include <ESP8266WiFi.h>
#define buzzerPin  5  // D1 (GPIO5)

// 음계의 배열을 만들고 배열에 들어가는 인자의 갯수를 8개로 지정합니다.
// 음계는 4옥타브를 기준으로 도, 레, 미, 파, 솔, 라, 시, 도를 출력합니다.
int numTones = 8;
int tones[] = {261, 294, 330, 349, 392, 440, 494, 523};

const char* ssid     = "MTPC4-NEW(2G)";
const char* password = "10821082";

int buzzerState = HIGH;

WiFiServer server(80);   // 웹서버용 포트 번호

void setup() { 
  Serial.begin(9600);  
  pinMode(buzzerPin, OUTPUT);
  //digitalWrite(buzzerPin, HIGH);

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("WiFi connected!!");

  // 웹서버 개시
  server.begin();
  Serial.println("Server started");

  // 접속할 IP 주소 표시
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  Serial.println("");  
}

void loop() {
  // 클라이언트가 접속되었는지 확인
  WiFiClient client = server.available();   
  if(!client) {  
    return;
  } 

  // 클라이언트가 데이터를 보낼 때까지 기다림
  Serial.println("new client");
  while(!client.available()) {
    delay(1);
  }

  // 리퀘스트의 첫번째 줄을 읽어들임
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // 리퀘스트에 따른 부저 제어
  if(request.indexOf("BZ_ON") != -1) {
    // digitalWrite(buzzerPin, HIGH);
    for (int i = 0; i < numTones; i++) {
      tone(buzzerPin, tones[i]);
      delay(500);
    }
    noTone(buzzerPin);    
    buzzerState = HIGH;   
  }
  if(request.indexOf("BZ_OFF") != -1) {
    
    // digitalWrite(buzzerPin, LOW);
    buzzerState = LOW;
  }

  // 클라이언트 리퀘스트에 대한 응답 메시지
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<body>");
  client.println("<br><br>");
  client.println("<a href=\"/BZ_ON\"\"><button>Play On</button></a>");
  client.println("<a href=\"/BZ_OFF\"\"><button>Play Off</button></a>");
  client.println("</html>");
  
  delay(1);
  Serial.println("Client disconnected!!");
  Serial.println();        
}
