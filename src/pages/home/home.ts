import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import { AngularFireDatabase } from 'angularfire2/database';

@Component({
  selector: 'page-home',
  templateUrl: 'home.html'
})
export class HomePage {
  temp:any;
  //time:any;
  public led1=0;
  public led2=0;
  public M=0;
  public time=0;
  public time1='';

  constructor(public navCtrl: NavController,  private db: AngularFireDatabase) {
    this.db.object('Home1/board1').valueChanges().subscribe(data=>{
      this.temp = data['temperature'];
      console.log(data['temperature']);
   });

   this.db.object('Home1/board1/Clock').valueChanges().subscribe(data=>{
    this.time = data['segment'];
    console.log(data['segment']);
 });



}

  led1Switch(){
    console.log(this.led1);
    const itemRef = this.db.object('Home1/board1/led');
    itemRef.update({led1:this.led1});
  }

  led2Switch(){
    console.log(this.led2);
    const itemRef = this.db.object('Home1/board1/led');
    itemRef.update({LED2:this.led2});
  }
  MM(){
    console.log(this.M);
    const itemRef = this.db.object('Home1/board1/Clock');
    itemRef.update({M:this.M});
  }

  timer(){
    console.log(this.time1);
    const itemRef2 = this.db.object('Home1/board1/Clock');
    itemRef2.update({segment:this.time1});
  }

}
