import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { TempModel } from '../models/temp.model';
import { InfluxClient } from '../shared/influx.client';

@Injectable({
  providedIn: 'root'
})
export class TemperaturaService {
  data = [65, 59, 80, 81, 56, 55, 40];
  lineChartLabels = ['January', 'February', 'March', 'April', 'May', 'June', 'July'];
  url = '';
  constructor(public httpClient: HttpClient, public influxClient: InfluxClient) { }

  getTemperatureValues():Observable<TempModel[]>{
    return this.httpClient.get(this.url) as Observable<TempModel[]>;
  }
}
