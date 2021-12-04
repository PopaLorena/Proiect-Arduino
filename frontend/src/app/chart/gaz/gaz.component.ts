import { Component, OnInit } from '@angular/core';
import { ChartDataSets, ChartOptions, ChartType } from 'chart.js';
import { Color, Label } from 'ng2-charts';
import { ThemeService } from 'ng2-charts';
import { GasModel } from 'src/app/models/gas.mode';
import { GazService } from 'src/app/services/gaz.service';

@Component({
  selector: 'app-gaz',
  templateUrl: './gaz.component.html',
  styleUrls: ['../chart.scss']
})
export class GazComponent implements OnInit {

  constructor(private gazService: GazService) { }
  gas: GasModel[] = [];

  ngOnInit(): void {
    this.gazService.getGasValues().subscribe(data =>{
      this.gas = data as GasModel[];
      console.log(this.gas[0].value);
      console.log(this.gas[0].date);
    })
  }
  // Array of different segments in chart
  lineChartData: ChartDataSets[] = [
    { data: [...this.gazService.data], label: 'gaz' }
  ];

  //Labels shown on the x-axis
  lineChartLabels: Label[] = [...this.gazService.gaz];


  // Define chart options
  lineChartOptions: ChartOptions = {
    responsive: true,

  };

  // Define colors of chart segments
  lineChartColors: Color[] = [
    { // dark grey
      hoverBorderColor: '#fafafa',
      backgroundColor: '#8c8e91',
      borderColor: 'rgba(77,83,96,1)',
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


  lineChartPlugins = [];




}
