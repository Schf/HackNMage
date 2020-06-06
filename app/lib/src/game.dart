import 'dart:ui';

import 'package:flame/text_config.dart';
import 'package:flame/position.dart';
import 'package:flame/game.dart';

import 'package:flutter/material.dart';


class HacknMage extends Game {
  Size screenSize;
  @override
  void render(Canvas canvas) {
      
    Rect bgRect = Rect.fromLTWH(0, 0, screenSize.width, screenSize.height);
    Paint bgPaint = Paint();
    bgPaint.color = Color(0xff000000);
    canvas.drawRect(bgRect, bgPaint);
    bgPaint.color = Color(0xf5f5f5f5);
    Rect novo1 = Rect.fromLTRB(10, 10, 40, 40);
    canvas.drawRect(novo1, bgPaint);
    bgPaint.color = Color(0xff0000ff);
    Rect novo2 = Rect.fromLTRB(40, 10, 70, 40);
    canvas.drawRect(novo2, bgPaint);
    bgPaint.color = Color(0xff00ff00);
    Rect novo3 = Rect.fromLTRB(70, 10, 100, 40);
    canvas.drawRect(novo3, bgPaint);
    bgPaint.color = Color(0xffff0000);
    bgPaint.color = Color(0xffffffff);
    Rect novo4 = Rect.fromLTRB(100, 10, 130, 40);
    canvas.drawRect(novo4, bgPaint);
    const TextConfig config = TextConfig(fontSize: 12.0, fontFamily: 'Roboto Mono');
    config.render(canvas, "aaa\niil\nmnm", Position(10, 10));
  }
  
  @override
  void update(double t) {
    // TODO: implement update
  }

  @override
  void resize(Size size){
    screenSize = size;
    super.resize(size);
  }  

}