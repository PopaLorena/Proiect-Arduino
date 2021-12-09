package ProiectArduino.models;

import java.time.Instant;

public class Gas {

    public Double value;
    public Instant date;

    public Double getValue() {
        return value;
    }

    public void setValue(Double value) {
        this.value = value;
    }

    public Instant getDate() {
        return date;
    }

    public void setDate(Instant date) {
        this.date = date;
    }

    public Gas(Double value, Instant date) {
        this.value = value;
        this.date = date;
    }
}
