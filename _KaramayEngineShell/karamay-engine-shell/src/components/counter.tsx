import React from 'react'
import {Container, Row, Alert, Button, Col} from 'react-bootstrap'

const counter: React.FC = () =>{
    return(
        <div>
            <Container fluid>
                <Row>
                    <Col>1of1</Col>
                </Row>
            </Container>

            <h2>0</h2>
            <button>+</button>
            <Button variant="success">++</Button>
            <Alert variant="primary">pick me up</Alert>
            
        </div>
    )
}

export default counter