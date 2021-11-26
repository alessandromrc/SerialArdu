class SerialArdu {
  private:
    // protocol statuses
    const String send = "0";
    const String err = "2";
    bool err_flag = false;
    bool val_flag = false;

    // protocol delimiters
    const char StartCMD = 1;
    const char FinishCMD = 2;

    String GetData(String input) {
      String sub = "";
      String Checksum = "";

      if (input.charAt(0) == '0') {
        if (input.charAt(1) == StartCMD) {
          int pos = input.indexOf(FinishCMD);
          sub = input.substring(2, pos);
          Checksum = input.substring(pos + 1, input.length());
        }

        // Checksum flag

        if (checksumCalculator(sub) == Checksum.toInt()) {
          err_flag = false;
          val_flag = true;
          return sub;
        } else {
          err_flag = true;
          val_flag = false;
        }
      }
      return "";
    }

  public:
    void ledStatus(byte pin_valid, byte pin_err) {
      digitalWrite(pin_valid, val_flag);
      digitalWrite(pin_err, err_flag);
    }

    int checksumCalculator(String data) {
      int count = 0;
      for (unsigned int i = 0; i <= data.length(); i++) {
        if (count % 2) data += data.charAt(i);
        count++;
      }
      return count;
    }

    void SendData(String data) {
      String DataStr;
      DataStr.concat(send);
      DataStr.concat(StartCMD);
      DataStr.concat(data);
      DataStr.concat(FinishCMD);
      DataStr.concat(checksumCalculator(data));
      Serial.println(DataStr);
    }
    String ReceiveData() {
      String incomingData = Serial.readStringUntil('\n');
      return this -> GetData(incomingData);
    }
};
