import React from 'react'
import ReactDOM from 'react-dom'
import 'bootstrap/dist/css/bootstrap.min.css'

import Counter from './counter'


function render() {
  ReactDOM.render(
    <div>
      <Counter/>
    </div>  
    , document.body);
}

render();