import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { GasModel } from '../models/gas.mode';

@Injectable({
  providedIn: 'root'
})
export class GazService {

  gaz = ['January', 'February', 'March', 'April', 'May', 'June', 'July'];
  url = 'http://localhost:8080/statistics/gas';
  data = [80, 59, 80, 81, 56, 55, 40]
  constructor(public httpClient: HttpClient) { }

  getGasValues(): Observable<GasModel[]> {
    return this.httpClient.get(this.url) as Observable<GasModel[]>;
  }
  getGasValue(): Observable<GasModel> {
    return this.httpClient.get(this.url) as Observable<GasModel>;
  }
}
