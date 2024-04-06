import * as THREE from "three";
import {GLTFLoader} from "GLTFLoader";

// Constants
const spread = 3.5;
const distance = 2.5;

// Scene setup
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.setClearColor(0x000000);
document.body.appendChild(renderer.domElement);

// Lighting
const light = new THREE.AmbientLight(0x404040); // soft white light
scene.add(light);

// Loader
const loader = new GLTFLoader();

// Objects
let objects = []; // Array to store the objects that the raycaster should check for intersections

// Animation
let animate = function() {
    requestAnimationFrame(animate);
    objects.forEach((object) => object.rotation.y += 0.01);
    renderer.render(scene, camera);
}

// Load initial model
loadModel('/Public/Cross.glb', camera.position.clone());

// Start animation
animate();

// Raycaster
const raycaster = new THREE.Raycaster();
const mouse = new THREE.Vector2();

// Event listeners
window.addEventListener('click', onClick, false);

// Score
let score = 0; // Initialize score variable
let scoreElement = document.getElementById('score'); // Get the score element

// Functions
function loadModel(path) {
    loader.load(path, function (gltf) {
        // Get the direction in which the camera is looking
        let direction = new THREE.Vector3();
        camera.getWorldDirection(direction);

        // Set the position of the model to be the same as the camera's position
        gltf.scene.position.copy(camera.position);
        // Move the model along the camera's direction
        gltf.scene.position.add(direction.multiplyScalar(distance));

        // Add a spread
        gltf.scene.position.x += (Math.random() - 0.5) * spread;
        gltf.scene.position.y += (Math.random() - 0.5) * spread;

        gltf.scene.rotation.set(0, Math.PI / 2, 0);
        gltf.scene.traverse((child) => {
            if (child.isMesh) {
                child.material = new THREE.MeshBasicMaterial({color: 0xffffff});
                objects.push(child);
            }
        });
        scene.add(gltf.scene);
    }, undefined, function (error) {
        console.error(error);
    });
}

function onClick(event) {
    event.stopPropagation();
    mouse.x = (event.clientX / window.innerWidth) * 2 - 1;
    mouse.y = -(event.clientY / window.innerHeight) * 2 + 1;
    raycaster.setFromCamera(mouse, camera);
    const intersects = raycaster.intersectObjects(objects, true);

    if (intersects.length > 0 && objects.includes(intersects[0].object)) {
        removeObject(intersects[0].object);
        loadNewModel();
        updateScore();
    } else {
        resetScore();
    }
}

function removeObject(object) {
    object.parent.remove(object);
    const index = objects.indexOf(object);
    if (index > -1) {
        objects.splice(index, 1);
    }
}

function loadNewModel() {
    let modelPosition = camera.position.clone();
    modelPosition.x += (Math.random() - 0.5) * spread;
    modelPosition.y += (Math.random() - 0.5) * spread;
    modelPosition.z -= distance;
    loadModel('/Public/Cross.glb', modelPosition);
}

function updateScore() {
    score++;
    scoreElement.textContent = 'Score: ' + score;
}

function resetScore() {
    score = 0;
    scoreElement.textContent = 'Score: ' + score;
}