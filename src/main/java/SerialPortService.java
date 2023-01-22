package sample;

import com.fazecast.jSerialComm.SerialPort;

import java.io.OutputStream;

import static com.fazecast.jSerialComm.SerialPort.getCommPort;

public class SerialPortService {
    private SerialPortService() {}

    public static SerialPort getSerialPort(String portDescriptor) {
        var sp = SerialPort.getCommPort(portDescriptor);

        var outputStream = sp.getOutputStream();
        sp.setComPortParameters(9600, Byte.SIZE, SerialPort.ONE_STOP_BIT, SerialPort.NO_PARITY);
        sp.setComPortTimeouts(SerialPort.TIMEOUT_NONBLOCKING,0,0);


        var hasOpened = sp.openPort();
        if (!hasOpened) {
            throw new IllegalStateException("Failed to open port.");
        }

        return sp;
    }


}
