import { Component } from '@angular/core';
import { NavController } from 'ionic-angular';
import { AngularFireDatabase } from 'angularfire2/database';

@Component({
  templateUrl: 'home2.html'
})
export class HomePage2 {
  
  public led1=0;
  public led2=0;
 

  constructor(public navCtrl: NavController,  private db: AngularFireDatabase) {}

  led1Switch(){
    console.log(this.led1);
    const itemRef = this.db.object('Home2/board1');
    itemRef.update({led1:this.led1});
  }

  led2Switch(){
    console.log(this.led2);
    const itemRef = this.db.object('Home2/board1');
    itemRef.update({led2:this.led2});
  }

}
