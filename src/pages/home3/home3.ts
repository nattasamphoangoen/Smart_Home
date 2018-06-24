import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import { AngularFireDatabase } from 'angularfire2/database';

@Component({
  templateUrl: 'home3.html'
})
export class HomePage3 {
  temp:any;
  public M=0;
  public time=0;
  public time1='';

  constructor(public navCtrl: NavController,  private db: AngularFireDatabase) {
    this.db.object('Home3/board1').valueChanges().subscribe(data=>{
      this.temp = data['temperature'];
      console.log(data['temperature']);
   });

   this.db.object('Home3/board1/Clock').valueChanges().subscribe(data=>{
    this.time = data['segment'];
    console.log(data['segment']);
 });



}
  MM(){
    console.log(this.M);
    const itemRef = this.db.object('Home3/board1/Clock');
    itemRef.update({M:this.M});
  }

  timer(){
    console.log(this.time1);
    const itemRef2 = this.db.object('Home3/board1/Clock');
    itemRef2.update({segment:this.time1});
  }

}
