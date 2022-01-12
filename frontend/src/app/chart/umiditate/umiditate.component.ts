import { Component, OnInit } from '@angular/core';
import { Color, Label } from 'ng2-charts';
import { UmidityModel } from 'src/app/models/umidity.model';
import { UmiditateService } from 'src/app/services/umiditate.service';
import { TemperaturaService } from 'src/app/services/temperatura.service';

@Component({
  selector: 'app-umiditate',
  templateUrl: './umiditate.component.html',
  styleUrls: ['./umiditate.component.scss']
})
export class UmiditateComponent implements OnInit {

  constructor(private umiditateService: UmiditateService) { }

  // apa?: TempApaModel;
  Data = [
    { apa: 22, time: '12:00' },
    { apa: 23, time: '13:00' },
    { apa: 24, time: '14:00' },
    { apa: 24, time: '15:00' },
    { apa: 24, time: '16:00' },
    { apa: 24, time: '17:00' },
    { apa: 24, time: '18:00' },];

  humidity: UmidityModel[] = [];

  ngOnInit(): void {
    this.umiditateService.getUmidityValues().subscribe(data => {
      this.humidity = data as UmidityModel[];
      console.log(this.humidity[0].value);
      console.log(this.humidity[0].date);
    })
  }

}
