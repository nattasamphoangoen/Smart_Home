import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { AngularFireDatabase } from 'angularfire2/database';
import { AlertController } from 'ionic-angular';
import { HomePage } from '../home/home';
import { HomePage2 } from '../home2/home2';
import { HomePage3 } from '../home3/home3';
import { HomePage4 } from '../home4/home4';

@Component({
    templateUrl: 'login.html'
  })
  export class Login {
    public user='';
    public pass='';

    public user2='';
    public pass2='';

    public user1='';
    public pass1='';

    public user3='';
    public pass3='';

    public user4='';
    public pass4='';
    selectedItem: any;
    selectedItem1: any;
    selectedItem2: any;
    selectedItem4: any;
  
    constructor(public navCtrl: NavController,  private db: AngularFireDatabase,public alertCtrl: AlertController
        , public navParams: NavParams){
       
    this.selectedItem = navParams.get('item');
    this.selectedItem1 = navParams.get('item2');
    this.selectedItem2 = navParams.get('item3');
    this.selectedItem4 = navParams.get('item4');

    this.db.object('Home1/board1').valueChanges().subscribe(data=>{
        this.user = data['User'];
        console.log(data['User']);
     });
  
     this.db.object('Home1/board1').valueChanges().subscribe(data=>{
      this.pass = data['Pass1'];
      console.log(data['Pass1']);
   });

   this.db.object('Home2/board1').valueChanges().subscribe(data=>{
    this.user2 = data['User'];
    console.log(data['User']);
 });

 this.db.object('Home2/board1').valueChanges().subscribe(data=>{
  this.pass2 = data['pass'];
  console.log(data['pass']);
});

this.db.object('Home3/board1').valueChanges().subscribe(data=>{
  this.user3 = data['User'];
  console.log(data['User']);
});

this.db.object('Home3/board1').valueChanges().subscribe(data=>{
this.pass3 = data['pass'];
console.log(data['pass']);
});

this.db.object('Home4').valueChanges().subscribe(data=>{
  this.user4 = data['User'];
  console.log(data['User']);
});

this.db.object('Home4').valueChanges().subscribe(data=>{
this.pass4 = data['pass'];
console.log(data['pass']);
});

    }
    
  showAlert(item2, item, item3, item4) {
      if((this.user == this.user1 && this.pass1 == this.pass)){
        this.navCtrl.push(HomePage, {
            item: item
          });
        }else if((this.user2 == this.user1 && this.pass1 == this.pass2)){
            this.navCtrl.push(HomePage2, {
                item2: item2
              });
        }else if((this.user3 == this.user1 && this.pass1 == this.pass3)){
          this.navCtrl.push(HomePage3, {
            item3: item3
          });
        }else if((this.user4 == this.user1 && this.pass1 == this.pass4)){
          this.navCtrl.push(HomePage4, {
            item4: item4
          });
        }else{
            const alert = this.alertCtrl.create({
                title: 'Please spare',
                subTitle: 'Not username and password',
                buttons: ['OK']
              });
              alert.present();
      }
    }
  }
  
  
  