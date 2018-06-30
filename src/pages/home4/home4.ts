import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import { AngularFireDatabase } from 'angularfire2/database';

@Component({
  templateUrl: 'home4.html'
})
export class HomePage4 {
  
  public led1 = "false";
  
  constructor(public navCtrl: NavController,  private db: AngularFireDatabase) {}

  led1Switch(){
    console.log(this.led1);
    const itemRef = this.db.object('Home4/led');
    itemRef.update({led1:this.led1});
  }


}
