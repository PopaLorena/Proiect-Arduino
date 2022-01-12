import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { UmidityModel } from '../models/umidity.model';

@Injectable({
  providedIn: 'root'
})
export class UmiditateService {

  url = 'http://localhost:8080/statistics/humidity';

  constructor(public httpClient: HttpClient) { }

  getUmidityValues(): Observable<UmidityModel[]> {
    return this.httpClient.get(this.url) as Observable<UmidityModel[]>;
  }
  getUmidityValue(): Observable<UmidityModel> {
    return this.httpClient.get(this.url) as Observable<UmidityModel>;
  }
}
