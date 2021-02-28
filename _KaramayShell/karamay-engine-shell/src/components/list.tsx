
import React from 'react';
import { render } from 'react-dom';

const ProfilePic = (props:string) => {
  return (
    <img src={'http://graph.facebook.com/' + props.username + '/picture'} />
  );
}

const ProfileLink = (props) => {
  return (
    <a href={'http://www.facebook.com/' + props.username}>
      {props.username}
    </a>
  );
}

const Avatar = (props) => {
  return (
    <div>
      <ProfilePic username={props.username} />
      <ProfileLink username={props.username} />
    </div>
  );
}

render(
  <Avatar username="pwh" />,
  document.getElementById('example')
);