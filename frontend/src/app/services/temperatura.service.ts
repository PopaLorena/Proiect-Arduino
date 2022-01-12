import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { TempModel } from '../models/temp.model';

@Injectable({
  providedIn: 'root'
})
export class TemperaturaService {

  url = 'http://localhost:8080/statistics/temperature';
  constructor(public httpClient: HttpClient) { }

  getTemperatureValues(): Observable<TempModel[]> {
    return this.httpClient.get(this.url) as Observable<TempModel[]>;
  }
  getTemperatureValue(): Observable<TempModel> {
    return this.httpClient.get(this.url) as Observable<TempModel>;
  }
}
