import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-view-page',
  templateUrl: './view-page.component.html',
  styleUrls: ['./view-page.component.scss']
})
export class ViewPageComponent implements OnInit {

  constructor() { }
  gaz = 5.3;
  temp = 2.4;
  apa = 4.8;
  ngOnInit(): void {
  }

}