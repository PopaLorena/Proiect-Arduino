import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.scss']
})
export class DashboardComponent implements OnInit {

  chart = 1;
  constructor() { }

  ngOnInit(): void {
  }
  next() {
    if (this.chart == 3) {
      this.chart = 1;
    }
    else
      this.chart++;

  }
}
