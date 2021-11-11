import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { UmidityModel } from '../models/umidity.model';

@Injectable({
  providedIn: 'root'
})
export class UmiditateService {
  data = [65, 59, 80, 81, 56, 55, 40];
  url = '';
  lineChartLabels = ['January', 'February', 'March', 'April', 'May', 'June', 'July'];
  constructor(public httpClient: HttpClient) { }

  getUmidityValues(): Observable<UmidityModel[]>{
    return this.httpClient.get(this.url) as Observable<UmidityModel[]>;
  }
}
