#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <esp_now.h>

uint8_t sendAddr[ESP_NOW_ETH_ALEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

const String alphabet = "abkdefhylmorstvx";
typedef struct message {
  int ID;
  int char_index;
  bool is_char;
} message;


class Button {
  private:
    int previous_state = LOW;
    unsigned long last_press_time = 0;
  public:
    int input_pin;

    Button(int pin) 
    {
      input_pin = pin;
      pinMode(input_pin, INPUT);
    }
    int pressTime()
    {
      int current_state = digitalRead(input_pin);
      if(current_state!=previous_state)
      {
        previous_state = current_state;
        if(!current_state)
        {
          return millis() - last_press_time;
        }
        last_press_time = millis();
      }
      return 0;
    }
    bool clicked()
    {
      if(pressTime()>50)
      {
        return true;
      }
      return false;
    }
    bool pressed()
    {
      bool current_state = digitalRead(input_pin);
      return current_state;
    }
    void reset()
    {
      previous_state = LOW;
      last_press_time = 0;
    }
};


message data;
void OnDataRecv(const uint8_t * mac, const uint8_t *received_data, int len)
{
  memcpy(&data, received_data, sizeof(data));
  /*
  if(data.ID <= analogRead(POTENTIOMETER_PIN)+50 and data.ID>=analogRead(POTENTIOMETER_PIN)-50)
  {
    check if both devices are using the same ID
    //get data from the other device
  }*/
  Serial.println("MAC Address: ");
  for (int i = 0; i < ESP_NOW_ETH_ALEN; i++) {
    Serial.printf("%02x", mac[i]);
    if (i < 5) {
      Serial.print(":");
    }
  }
  Serial.println("Bytes received: ");
  Serial.print(len);
  Serial.println("Message received: ");
  if(data.is_char)
  {
    Serial.print(alphabet[data.char_index]);
  }
  else
  {
    Serial.print(data.char_index);
  }
}

message msg;
esp_now_peer_info_t peerInfo;
Button button0(4);
Button button1(16);
void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  
  ESP_ERROR_CHECK(esp_now_init());
  ESP_ERROR_CHECK(esp_now_register_recv_cb(OnDataRecv));

  memcpy(peerInfo.peer_addr, sendAddr, ESP_NOW_ETH_ALEN);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  ESP_ERROR_CHECK(esp_now_add_peer(&peerInfo));

  msg.ID = random(0, 100);
  msg.char_index = 0;
  msg.is_char = true;
}

int c=0;
void loop()
{
  if(c>=4)
  {
    digitalWrite(2, HIGH);
    if(esp_now_send(sendAddr, (uint8_t *) &msg, sizeof(msg)) != ESP_OK)
    {
      delay(2000);
    }
    digitalWrite(2, LOW);
    c = 0;
    msg.char_index = 0;
    button0.reset();
    button1.reset();
  }
  if(button0.pressed() and button1.pressed())
  {
    msg.is_char = !msg.is_char;
    button0.reset();
    button1.reset();
  }
  else if(button1.clicked())
  {
    Serial.println("Button 1 clicked");
    msg.char_index += pow(2, c);
  }
  if(button0.clicked() or button1.clicked())
  {
    c++;
  }
}