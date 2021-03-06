package ProiectArduino.Influx;

import ProiectArduino.models.*;
import com.influxdb.client.InfluxDBClient;
import com.influxdb.client.InfluxDBClientFactory;
import com.influxdb.query.FluxRecord;
import com.influxdb.query.FluxTable;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class InfluxDBConnection {

    // You can generate an API token from the "API Tokens Tab" in the UI
    String token = "55trP1i-mBCyoUNGlbLwiRuz-dZ4HTB368xsU_j-JoxKEbxSTxhUhcATze2TResaeP1dCiSegd3yH1QgVgdYCw==";
    String bucket = "ArduinoESP";
    String org = "arduinosio2021@gmail.com";

    List<Temperature> tempList = new ArrayList<>();
    List<Gas> gasList = new ArrayList<>();
    List<Humidity> humidityList = new ArrayList<>();
    Buzzer buzzer;
    PIR PIR;

    InfluxDBClient client = InfluxDBClientFactory.create("https://eu-central-1-1.aws.cloud2.influxdata.com", token.toCharArray());

    public List<Temperature> getTempList() {
        return tempList;
    }

    public void setTempList(List<Temperature> tempList) {
        this.tempList = tempList;
    }

    public List<Gas> getGasList() {
        return gasList;
    }

    public void setGasList(List<Gas> gasList) {
        this.gasList = gasList;
    }

    public List<Humidity> getHumidityList() {
        return humidityList;
    }

    public void setUmidityList(List<Humidity> humidityList) {
        this.humidityList = humidityList;
    }

    public Buzzer getBuzzer() {
        return buzzer;
    }

    public void setBuzzer(Buzzer buzzer) {
        this.buzzer = buzzer;
    }

    public ProiectArduino.models.PIR getPIR() {
        return PIR;
    }

    public void setPIR(ProiectArduino.models.PIR PIR) {
        this.PIR = PIR;
    }

    public void read(){
        String query = "from(bucket: \"ArduinoESP\") |> range(start: -30d)";
        List<FluxTable> tables = client.getQueryApi().query(query, org);

        for (FluxTable table : tables) {
            for (FluxRecord record : table.getRecords()) {
                if (record.getField().equals("Temp")){
                    this.tempList.add(new Temperature((Double) record.getValue(), record.getTime()));
                }

                if (record.getField().equals("GAZ")){
                    this.gasList.add(new Gas((Double) record.getValue(), record.getTime()));
                }

                if (record.getField().equals("Humidity")){
                    this.humidityList.add(new Humidity((Double) record.getValue(), record.getTime()));
                }

                if (record.getField().equals("Buzzer")){
                    this.buzzer = new Buzzer((Long) record.getValue(), record.getTime());
                }

                if (record.getField().equals("PIR")){
                    this.PIR = new PIR((Long) record.getValue(), record.getTime());
                }
            }
        }

        client.close();
    }
}
