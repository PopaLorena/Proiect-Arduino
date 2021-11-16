package ProiectArduino.controllers;

import ProiectArduino.Influx.InfluxDBConnection;
import ProiectArduino.models.Gas;
import ProiectArduino.models.Humidity;
import ProiectArduino.models.Temperature;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@RequestMapping("/statistics")
public class StatisticsController {

    public InfluxDBConnection influxDBConnection;

    @Autowired
    public StatisticsController(InfluxDBConnection influxDBConnection) {
        this.influxDBConnection = influxDBConnection;
    }

        @GetMapping("/temperature")
    public ResponseEntity<List<Temperature>> getTemperature(){
        influxDBConnection.read();
        return new ResponseEntity<>(influxDBConnection.getTempList(), HttpStatus.OK);
    }

    @GetMapping("/humidity")
    public ResponseEntity<List<Humidity>> getHumidity(){
        influxDBConnection.read();
        return new ResponseEntity<>(influxDBConnection.getHumidityList(), HttpStatus.OK);
    }

    @GetMapping("/gas")
    public ResponseEntity<List<Gas>> getGas(){
        influxDBConnection.read();
        return new ResponseEntity<>(influxDBConnection.getGasList(), HttpStatus.OK);
    }
}
