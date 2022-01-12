import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class SharedService {
  url = 'http://localhost:8080/statistics/';
  constructor(public httpClient: HttpClient) { }

  getBuzzerValue(): Observable<Number> {
    return this.httpClient.get(this.url + "buzzer") as Observable<Number>;
  }

  getPIRValue(): Observable<Number> {
    return this.httpClient.get(this.url + "PIR") as Observable<Number>;
  }
}
