'use strict';

const infoTitle = document.querySelector('.info_text');
const tempButton = document.querySelector('#temp_display');
const prespButton = document.querySelector('#pressure_display');
const numButton = document.querySelector('#number_display');
const unitText = document.querySelector('.unit');

tempButton.addEventListener('click', function() {
    infoTitle.textContent = 'Temperature Sensor';
    unitText.textContent = '°C'
})

prespButton.addEventListener('click', function() {
    infoTitle.textContent = 'Pressure Sensor';
    unitText.textContent = ' Pa'
})

numButton.addEventListener('click', function() {
    infoTitle.textContent = 'Temperature & Pressure Sensor';
})

