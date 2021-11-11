import { Injectable } from "@angular/core";

declare var require: any;

const {InfluxDB} = require('influx');
const token = '55trP1i-mBCyoUNGlbLwiRuz-dZ4HTB368xsU_j-JoxKEbxSTxhUhcATze2TResaeP1dCiSegd3yH1QgVgdYCw==';
const org = 'arduinosio2021@gmail.com';
const bucket = 'ArduinoESP';

const query = `from(bucket: "ArduinoESP") |> range(start: -1h)`;

Injectable({
    providedIn: 'root'
})
export class InfluxClient{

    client = new InfluxDB({url: 'https://eu-central-1-1.aws.cloud2.influxdata.com', token: token});
    queryApi = this.client.getQueryApi(org);


    constructor(){}

    getClient(){
        return this.client;
    }

    getQuery(){
        console.log(
            this.queryApi.queryRows(query, {
                next(row: any, tableMeta: { toObject: (arg0: any) => any; }) {
                  const o = tableMeta.toObject(row)
                  console.log(`${o._time} ${o._measurement}: ${o._field}=${o._value}`)
                },
                error(error: any) {
                  console.error(error)
                  console.log('Finished ERROR')
                },
                complete() {
                  console.log('Finished SUCCESS')
                },
              })
        );
    }
}