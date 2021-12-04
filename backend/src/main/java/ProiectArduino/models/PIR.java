package ProiectArduino.models;

import java.time.Instant;

public class PIR {

    Long PIR;
    public Instant date;

    public PIR(Long PIR, Instant date) {
        this.PIR = PIR;
        this.date = date;
    }

    public Long getPIR() {
        return PIR;
    }

    public void setPIR(Long PIR) {
        this.PIR = PIR;
    }

    public Instant getDate() {
        return date;
    }

    public void setDate(Instant date) {
        this.date = date;
    }
}
