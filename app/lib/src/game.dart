import 'dart:ui';

import 'package:flame/game.dart';

import 'package:flutter/material.dart';
import 'package:app/src/background.dart';
import 'package:app/src/map.dart';

class HacknMage extends BaseGame {
  Size screenSize;
  
  HacknMage(){
    add(Background());
    add(Map(widthSquares: 11, heightSquares: 15));
  }
  
  @override
  void update(double t) {}

  @override
  void resize(Size size){
    screenSize = size;
    super.resize(size);
  }  

}