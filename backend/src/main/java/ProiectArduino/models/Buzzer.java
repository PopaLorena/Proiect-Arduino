package ProiectArduino.models;

import java.time.Instant;

public class Buzzer {

    Long buzzer;
    public Instant date;

    public Buzzer(Long buzzer, Instant date) {
        this.buzzer = buzzer;
        this.date = date;
    }

    public Long getBuzzer() {
        return buzzer;
    }

    public void setBuzzer(Long buzzer) {
        this.buzzer = buzzer;
    }

    public Instant getDate() {
        return date;
    }

    public void setDate(Instant date) {
        this.date = date;
    }
}
