import React, { Component } from "react";
import Sketch from "react-p5";
import p5sound from "p5";
import "p5/lib/addons/p5.sound"
 
export default class App extends Component {
  x = 50;
  y = 50;
  constructor (props) {
    super(props);
    this.state= {
      fft: new p5sound.FFT(),
    }
  }
 
  setup = (p5, canvasParentRef) => {
    p5.createCanvas(500, 500).parent(canvasParentRef); // use parent to render canvas in this ref (without that p5 render this canvas outside your component)
  //  console.log(new p5sound.FFT());
  };
  draw = p5 => {
    p5.background(0);
    p5.ellipse(this.x, this.y, 70, 70);
    // NOTE: Do not use setState in draw function or in functions that is executed in draw function... pls use normal variables or class properties for this purposes
    this.x++;
  };
 
  render() {
    return <Sketch setup={this.setup} draw={this.draw} />;
  }
}