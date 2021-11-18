package ProiectArduino.controllers;

import ProiectArduino.Influx.InfluxDBConnection;
import ProiectArduino.models.Gas;
import ProiectArduino.models.Humidity;
import ProiectArduino.models.Temperature;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/statistics")
public class StatisticsController {

    public InfluxDBConnection influxDBConnection;

    @Autowired
    public StatisticsController(InfluxDBConnection influxDBConnection) {
        this.influxDBConnection = influxDBConnection;
        influxDBConnection.read();
    }

    @GetMapping("/temperature")
    public ResponseEntity<List<Temperature>> getTemperature(){
        return new ResponseEntity<>(influxDBConnection.getTempList().stream().skip(influxDBConnection.getTempList().size() - 10).collect(Collectors.toList()), HttpStatus.OK);
    }

    @GetMapping("/humidity")
    public ResponseEntity<List<Humidity>> getHumidity(){
        return new ResponseEntity<>(influxDBConnection.getHumidityList().stream().skip(influxDBConnection.getTempList().size() - 10).collect(Collectors.toList()), HttpStatus.OK);
    }

    @GetMapping("/gas")
    public ResponseEntity<List<Gas>> getGas(){
        return new ResponseEntity<>(influxDBConnection.getGasList().stream().skip(influxDBConnection.getTempList().size() - 10).collect(Collectors.toList()), HttpStatus.OK);
    }
}
