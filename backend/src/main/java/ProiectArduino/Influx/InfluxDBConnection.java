package ProiectArduino.Influx;

import com.influxdb.client.InfluxDBClient;
import com.influxdb.client.InfluxDBClientFactory;
import com.influxdb.query.FluxRecord;
import com.influxdb.query.FluxTable;
import ProiectArduino.models.Gas;
import ProiectArduino.models.Temperature;
import ProiectArduino.models.Umidity;
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
    List<Umidity> umidityList = new ArrayList<>();

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

    public List<Umidity> getUmidityList() {
        return umidityList;
    }

    public void setUmidityList(List<Umidity> umidityList) {
        this.umidityList = umidityList;
    }

    public void read(){
        String query = "from(bucket: \"ArduinoESP\") |> range(start: -1h)";
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
                    this.umidityList.add(new Umidity((Double) record.getValue(), record.getTime()));
                }
            }
        }

        client.close();
    }
}
