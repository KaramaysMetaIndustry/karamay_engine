import React from 'react';
import ReactDOM from 'react-dom';
import {Container, Row, Alert, Button, Col} from 'react-bootstrap';

const counter: React.FC = () =>{
    return(
        <div>
            <Container fluid>
                <Row>
                    <Col><Button variant="success">++</Button></Col>
                    <Col><Alert variant="primary">pick me up</Alert></Col>
                </Row>
            </Container>

            
            
            
        </div>
    )
}

export default counter