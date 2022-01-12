import { Component, OnInit } from '@angular/core';
import { SharedService } from 'src/app/services/shared.service';
import { GasModel } from '../models/gas.mode';
import { TempModel } from '../models/temp.model';
import { UmidityModel } from '../models/umidity.model';
import { GazService } from '../services/gaz.service';
import { TemperaturaService } from '../services/temperatura.service';
import { UmiditateService } from '../services/umiditate.service';

@Component({
  selector: 'app-view-page',
  templateUrl: './view-page.component.html',
  styleUrls: ['./view-page.component.scss']
})
export class ViewPageComponent implements OnInit {

  constructor(private sharedService: SharedService, private tempService: TemperaturaService, private umiditateService: UmiditateService, private gazService: GazService) {

  }
  gazData = 5.3;
  tempData = 2.4;
  apa = 4.8;
  interval: any;
  temp: TempModel[] = [];
  buzzer: number = -6;
  PIR?: Number;
  humidity: UmidityModel[] = [];
  gaz?: GasModel[];
  audio = new Audio();

  ngOnInit(): void {
    this.interval = setInterval(() => {
      this.sharedService.getBuzzerValue().subscribe(data => {
        //this.buzzer = data;
      });

      this.sharedService.getPIRValue().subscribe(data => {
        this.PIR = data;
      });
      this.getUmiditate();
      this.getTemp();
      this.getGaz();

      if (this.buzzer > 1 && this.buzzer < 7) {
        this.audio.src = "../../assets/mixkit-classic-alarm-995.wav";
        this.audio.load();
        this.audio.play();
      }
    }, 1000);
  }

  getUmiditate() {
    this.umiditateService.getUmidityValue().subscribe(data => {
      this.apa = data.value;
    })
  }

  getTemp() {
    this.tempService.getTemperatureValue().subscribe(data => {
      this.tempData = data.temp;
    })
  }

  getGaz() {
    this.gazService.getGasValue().subscribe(data => {
      this.gazData = data.value;
    })
  }

  ngOnDestroy() {

    if (this.interval) {
      clearInterval(this.interval);
    }
  }
}

