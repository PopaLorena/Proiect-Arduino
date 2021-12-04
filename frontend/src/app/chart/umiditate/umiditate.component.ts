import { Component, OnInit } from '@angular/core';
import { ChartDataSets, ChartOptions, ChartType } from 'chart.js';
import { Color, Label } from 'ng2-charts';
import { UmidityModel } from 'src/app/models/umidity.model';
import { UmiditateService } from 'src/app/services/umiditate.service';
@Component({
  selector: 'app-umiditate',
  templateUrl: './umiditate.component.html',
  styleUrls: ['../chart.scss']
})
export class UmiditateComponent implements OnInit {

  constructor(private umiditateService: UmiditateService) { }
  humidity: UmidityModel[] = [];

  ngOnInit(): void {
    this.umiditateService.getUmidityValues().subscribe(data =>{
      this.humidity = data as UmidityModel[];
      console.log(this.humidity[0].value);
      console.log(this.humidity[0].date);
    })
  }
  // Array of different segments in chart
  lineChartData: ChartDataSets[] = [
    { data: [...this.umiditateService.data], label: 'Umiditate' }
  ];

  //Labels shown on the x-axis
  lineChartLabels: Label[] = [...this.umiditateService.lineChartLabels];

  // Define chart options
  lineChartOptions: ChartOptions = {
    responsive: true
  };

  // Define colors of chart segments
  lineChartColors: Color[] = [


    { // blue
      backgroundColor: 'rgba(0,0,255,0.5)',
      borderColor: 'blue',
      pointBackgroundColor: '#fafafa',
      pointBorderColor: '#fafafa',
      pointHoverBackgroundColor: '#fafafa',
      pointHoverBorderColor: '#fafafa'
    }
  ];

  // Set true to show legends
  lineChartLegend = false;

  // Define type of chart
  lineChartType: ChartType = 'line';
  //pieChartType: ChartType = 'pie';

  lineChartPlugins = [];

  // events
  chartClicked({ event, active }: { event: MouseEvent, active: {}[] }): void {
    console.log(event, active);
  }

  chartHovered({ event, active }: { event: MouseEvent, active: {}[] }): void {
    console.log(event, active);
  }
}
