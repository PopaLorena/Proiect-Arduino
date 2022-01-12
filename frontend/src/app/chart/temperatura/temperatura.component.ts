import { Component, OnInit } from '@angular/core';
import { ChartDataSets, ChartOptions, ChartType } from 'chart.js';
import { List } from 'echarts';
import { Color, Label } from 'ng2-charts';
import { TempModel } from 'src/app/models/temp.model';
import { TemperaturaService } from 'src/app/services/temperatura.service';

export interface PeriodicElement {
  // time: string;
  temp: number;
}

@Component({
  selector: 'app-temperatura',
  templateUrl: './temperatura.component.html',
  styleUrls: ['./temperatura.component.scss']
})

export class TemperaturaComponent implements OnInit {
  interval: any;

  constructor(private tempService: TemperaturaService) { }

  // temp?: TempApaModel;
  date: Date = new Date;
  tempData: number[] = [2, 5];
  timeData?: String[] = ["12:00", "22:00"];
  Data = [
    { temp: 22, time: '12:00' },
    { temp: 23, time: '13:00' },
    { temp: 24, time: '14:00' },
    { temp: 24, time: '15:00' },
    { temp: 24, time: '16:00' },
    { temp: 24, time: '17:00' },
    { temp: 24, time: '18:00' },];

  temp: TempModel[] = [];
  var: any;


  ngOnInit(): void {
    this.tempService.getTemperatureValues().subscribe(data => {
      this.temp = data as TempModel[];
      console.log(this.temp[0].temp);
      console.log(this.temp[0].date);
    })

  }
  columns = [
    {
      columnDef: 'temp',
      header: 'temp',
      cell: (element: PeriodicElement) => `${element.temp}`,
    },
  ];
  dataSource = this.tempData;
  displayedColumns = this.columns.map(c => c.columnDef);
}


