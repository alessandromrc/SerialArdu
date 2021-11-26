const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const port = new SerialPort('COM7', { baudRate: 115200 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));
const StartCMD = String.fromCharCode(1);
const FinishCMD = String.fromCharCode(2);
const send = 0;

let err_flag = false;
let val_flag = false;

function checksumCalculator(data) {
  let count = 0;
  for (let i = 0; i <= data.length; i++) {
    if (count % 2) data += data.charAt(i);
    count++;
  }
  return count + 1 ;
}


function GetData(input) {
  let sub = "";
  let Checksum = "";

  if (input.charAt(0) == '0') {
    if (input.charAt(1) == StartCMD) {
      const pos = input.indexOf(FinishCMD);
      sub = input.substring(2, pos);
      Checksum = input.substring(pos + 1, input.length);
    }

    // Checksum flag

    if (checksumCalculator(sub) == parseInt(Checksum)) {
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


function SendData(input) {
  const DATA = send + StartCMD + data +  FinishCMD + checksumCalculator(input);
  console.log(DATA);
  port.write(DATA + '\n', (err) => {
    if (err) {
      return console.log('Error on write: ', err.message);
    }
    console.log('message written');
  });
}


const data = "led_on";


port.on("open", () => {
  console.log('serial port open');
  SendData(data);
});

parser.on('data', data =>{
  console.log(GetData(data));
});
