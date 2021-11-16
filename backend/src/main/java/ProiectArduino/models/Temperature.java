package ProiectArduino.models;

import java.time.Instant;

public class Temperature {

    public Double temp;
    public Instant date;

    public Double getTemp() {
        return temp;
    }

    public void setTemp(Double temp) {
        this.temp = temp;
    }

    public Instant getDate() {
        return date;
    }

    public void setDate(Instant date) {
        this.date = date;
    }

    public Temperature(Double temp, Instant date) {
        this.temp = temp;
        this.date = date;
    }
}
