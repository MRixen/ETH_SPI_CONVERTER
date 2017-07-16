#include <SPI.h>
#include "mcp_can.h"
#include <UIPEthernet.h>
#include "DEFINITIONS.h"

void setup() {

	Serial.begin(115200);

	while (CAN_OK != CAN.begin(CAN_250KBPS, MODE_NORMAL))            // init can bus : baudrate = 500k
	{
		Serial.println("CAN BUS Shield init fail");
		Serial.println(" Init CAN BUS Shield again");
		delay(100);
	}
	Serial.println("CAN BUS Shield init ok!");

	// User defined
	debugMode = true;

	// SPI interface is initialized in ethernet-library
	uint8_t mac[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };
	for (size_t i = 0; i < MESSAGE_SIZE_TCP; i++) bufferInTcp[i] = 0;

	Ethernet.begin(mac, IPAddress(192, 168, 0, 88));
}

void loop() {
	int size = 0;

	while (true) {
		if (client.connected()) {

			// Receive data from server
			// Receive the whole data to controlling 6 motors via tcp/ip
			if ((size = client.available()) > 0) {
				client.readBytes(bufferInTcp, MESSAGE_SIZE_TCP);
				//Serial.print("size: ");
				//Serial.println(size);
				//Serial.println("-");

				// Write data to spi 
				// Write for each motor 4 bytes via spi
				for (int i = 0; i < MAX_MOTOR_AMOUNT; i++)
				{
					for (size_t j = 0; j < MESSAGE_SIZE_SPI; j++) bufferOutSpi[j] = bufferInTcp[j + (i * 5)];

					CAN.sendMsgBuf(i+1, 0, MESSAGE_SIZE_SPI, bufferOutSpi);

					delay(5);

					//if (CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
					//{
					//	CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

					//	unsigned char canId = CAN.getCanId();

					//	Serial.println("-----------------------------");
					//	Serial.print("get data from ID: ");
					//	Serial.println(canId);

					//	for (int i = 0; i < len; i++)    // print the data
					//	{
					//		Serial.print(buf[i]);
					//		Serial.print("\t");
					//	}
					//	Serial.println();
					//}
				}
			}
		}
		else {
			client.connect(IPAddress(192, 168, 0, 222), 4001);
		}
	}
}