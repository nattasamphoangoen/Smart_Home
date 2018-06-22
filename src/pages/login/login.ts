import { Component } from '@angular/core';
import { NavController, NavParams } from 'ionic-angular';
import { AngularFireDatabase } from 'angularfire2/database';
import { AlertController } from 'ionic-angular';
import { HomePage } from '../home/home';

@Component({
    templateUrl: 'login.html'
  })
  export class Login {
    public user='';
    public pass='';
    public user1='';
    public pass1='';
  selectedItem: any;
  
  
    constructor(public navCtrl: NavController,  private db: AngularFireDatabase,public alertCtrl: AlertController
        , public navParams: NavParams){
       
    this.selectedItem = navParams.get('item');

    this.db.object('Home1/board1').valueChanges().subscribe(data=>{
        this.user = data['User'];
        console.log(data['User']);
     });
  
     this.db.object('Home1/board1').valueChanges().subscribe(data=>{
      this.pass = data['Pass1'];
      console.log(data['Pass1']);
   });

    }
    
  showAlert(event, item) {
      if((this.user == this.user1 && this.pass1 == this.pass)){
        this.navCtrl.push(HomePage, {
            item: item
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
  
  
  