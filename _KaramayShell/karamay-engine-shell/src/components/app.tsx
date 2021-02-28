import React from 'react'
import ReactDOM from 'react-dom'
import Counter from './counter'


function render() {
  ReactDOM.render(
    <div>
      <Counter/>
    </div>  
    , document.body);
}

render();