package sample;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortEvent;
import com.fazecast.jSerialComm.SerialPortMessageListenerWithExceptions;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.chart.XYChart;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.ByteBuffer;

public class DataController implements SerialPortMessageListenerWithExceptions {
    private static final byte[] DELIMITER = new byte[]{'\n'};
    private final ObservableList<XYChart.Data<Number, Number>> dataPoints;
    private final OutputStream outputStream;
    private final OutputStream outputStream2;
    public DataController(OutputStream outputStream,OutputStream outputStream2) {
        this.dataPoints = FXCollections.observableArrayList();
        this.outputStream=outputStream;
        this.outputStream2=outputStream2;

    }

    public ObservableList<XYChart.Data<Number, Number>> getDataPoints() {
        return dataPoints;
    }

    @Override
    public int getListeningEvents() {
        return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
    }

    @Override
    public void serialEvent(SerialPortEvent serialPortEvent) {

        if(serialPortEvent.getEventType() != SerialPort.LISTENING_EVENT_DATA_RECEIVED){
            System.out.println("!!!");
            return;
        }
        var data = serialPortEvent.getReceivedData();
        var value = ByteBuffer.wrap(data).getInt();//changing the data form the sensor to a numerical variable

        if (value==0){
            try {
                outputStream2.write(80);// Send byte value to second Arduino if the hand is detected to show the steps on the LCD in order
                outputStream.write(200);// Send byte value to Grove beginner kit if the hand is detected to turn the motor on
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        var time = System.currentTimeMillis();
        var dataPoint = new XYChart.Data<Number, Number>(time, value);

        Platform.runLater(() -> this.dataPoints.add(dataPoint));
    }

    @Override
    public void catchException(Exception e) {
        e.printStackTrace();
    }

    @Override
    public byte[] getMessageDelimiter() {
        return DELIMITER;
    }

    @Override
    public boolean delimiterIndicatesEndOfMessage() {
        return true;
    }
}