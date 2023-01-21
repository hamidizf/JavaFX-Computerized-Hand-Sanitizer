package sample;


import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.application.Application;
import javafx.beans.property.SimpleLongProperty;
import javafx.collections.FXCollections;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.stage.Stage;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.util.Timer;
import com.fazecast.jSerialComm.SerialPort;


public class Main extends Application {

    private final static int MAX_Sensor_VALUE = 1<< 1;


    public static void main(String[] args) {launch(args);}
    @Override
    public void start(Stage primaryStage) {
        var sp = SerialPortService.getSerialPort("/dev/cu.usbserial-0001");//port to Grove beginner kit to control Servo and gather data from sensor
        var sp2 = SerialPortService.getSerialPort("/dev/cu.usbmodem142101");// port to Arduino uno to control LCD
        var outputStream = sp.getOutputStream();
        var outputStream2 = sp2.getOutputStream();

        var hbox1 = new HBox();// create horizontal boxes to put buttons and the graph in the desired location
        hbox1.setSpacing(20.0);
        hbox1.setPadding(new Insets(50, 250, 50, 330));
        var button1 = new Button("Start LCD"); // create button for the LCD to show the steps in order
        button1.setOnMousePressed(value ->{
            try{
                outputStream2.write(101);//sending byte values to second Arduino
            }catch(IOException e){
                e.printStackTrace();
            }
        });
        var button2= new Button("Servo On");// create the button for the motor
        button2.setOnMousePressed(value ->{
            try{
                outputStream.write(255);//send byte values to the Grove beginner kit
            }catch(IOException e){
                e.printStackTrace();
            }
        });
        hbox1.getChildren().addAll(button1,button2); //putting two buttons in one horizontal box

        var hbox2 = new HBox();
        hbox2.setSpacing(10.0);
        hbox2.setPadding(new Insets(0, 0, 0, 380));
        var button3 = new Button("1"); // creating rest of the buttons to control LCD
        button3.setOnMousePressed(value ->{
            try{
                outputStream2.write(100);
            }catch(IOException e){
                e.printStackTrace();
            }
        });
        var button4 = new Button("2");
        button4.setOnMousePressed(value ->{
            try{
                outputStream2.write(99);
            }catch(IOException e){
                e.printStackTrace();
            }
        });
        var button5 = new Button("3");
        button5.setOnMousePressed(value ->{
            try{
                outputStream2.write(98);
            }catch(IOException e){
                e.printStackTrace();
            }
        });
        hbox2.getChildren().addAll(button3,button4,button5);
        var hbox3 = new HBox();
        hbox3.setSpacing(9.0);
        hbox3.setPadding(new Insets(0, 0, 0, 380));
        var button6 = new Button("4");
        button6.setOnMousePressed(value ->{
            try{
                outputStream2.write(121);
            }catch(IOException e){
                e.printStackTrace();
            }
        });
        var button7 = new Button("5");
        button7.setOnMousePressed(value ->{
            try{
                outputStream2.write(102);
            }catch(IOException e){
                e.printStackTrace();
            }
        });
        var button8 = new Button("6");
        button8.setOnMousePressed(value ->{
            try{
                outputStream2.write(103);
            }catch(IOException e){
                e.printStackTrace();
            }
        });

        hbox3.getChildren().addAll(button6,button7,button8);
        var hbox4= new HBox();
        hbox4.setSpacing(10.0);
        hbox4.setPadding(new Insets(0, 0, 0, 397));
        var button9 = new Button("7");
        button9.setOnMousePressed(value ->{
            try{
                outputStream2.write(104);
            }catch(IOException e){
                e.printStackTrace();
            }
        });
        var button10 = new Button("8");
        button10.setOnMousePressed(value ->{
            try{
                outputStream2.write(105);
            }catch(IOException e){
                e.printStackTrace();
            }
        });
        hbox4.getChildren().addAll(button9,button10);

        var now = System.currentTimeMillis();
        var hbox5= new HBox();
        var controller = new DataController(outputStream,outputStream2); // adding output streams to Data control to use them in the package for the manual System
        sp.addDataListener(controller);

        var xAxis = new NumberAxis("Time ", now, now + 50000, 10000000); // creates the x-axis (which automatically updates)
        var yAxis = new NumberAxis("Sensor Data", 0, MAX_Sensor_VALUE, 1); // creates the y-axis

        var series = new XYChart.Series<>(controller.getDataPoints()); // creates the series (all the data)
        var lineChart = new LineChart<>(xAxis, yAxis, FXCollections.singletonObservableList(series)); // creates the chart
        lineChart.setTitle("Sensor");
        series.setName("          My Live Graph ");

        hbox5.setPadding(new Insets(0, 80, 30, 170));
        hbox5.getChildren().addAll(lineChart); //moving the chart to box 5.



        var vbox = new VBox();
        vbox.setSpacing(10.0);
        vbox.setPadding(new Insets(0, 0, 0, 0));
        vbox.getChildren().addAll(hbox1, hbox2,hbox3,hbox4,hbox5); // adding all horizontal boxes to one vertical box

        var scene = new Scene(vbox, 850, 650);

        primaryStage.setScene(scene);
        primaryStage.show();




    }
}