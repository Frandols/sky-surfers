const socket = io.connect('http://localhost:5000')

const root = document.querySelector(':root')
const start = document.querySelector('.start')
const level = document.querySelector('.level')
const container = document.querySelector('.container')
const player = document.querySelector('.player')

setTimeout(
    () => start.style.setProperty(
        'display',
        'none'
    ),
    5000
)

class Bullet {
    node = null

    constructor({ shooter }) {
        this.shooter = shooter
    }

    deploy() {
        this.node = document.createElement('div')
        this.node.className = 'bullet'

        this.node.style.setProperty(
            'left',
            `${this.shooter.node.offsetLeft}px`
        )
        this.node.style.setProperty(
            'top',
            `${this.shooter.node.offsetTop}px`
        )
        
        container.appendChild(this.node)

        const h = 1200
        const a = player.offsetLeft - this.shooter.node.offsetLeft
        const b = player.offsetTop - this.shooter.node.offsetTop
        const angle = Math.atan(a / b)

        this.node.style.setProperty(
            'transform', 
            `translate(${h * Math.sin(angle)}px, ${h * Math.cos(angle)}px)`
        )

        setTimeout(
            () => this.destroy(),
            1.5 * 1000
        )
    }

    destroy() {
        container.removeChild(this.node)
    }
}

class Enemy {
    node = null
    ammunitionCount = 1

    constructor({ position }) {
        this.position = position
    }

    deploy() {
        this.node = document.createElement('div')
        this.node.className = 'enemy'

        this.node.style.setProperty(
            'left',
            `${this.position}px`
        )

        container.appendChild(this.node)

        const image = document.createElement('img')
        image.src = 'assets/img/enemy.png'
        image.width = 200
        image.height = 200

        this.node.appendChild(image)

        this.shoot()

        setTimeout(
            () => this.destroy(),
            5 * 1000
        )
    }

    shoot() {
        const bullet = new Bullet({ shooter: this })

        bullet.deploy()

        const shooting = setInterval(
            () => {
                if(this.ammunitionCount === 0) return clearInterval(shooting)

                const bullet = new Bullet({ shooter: this })

                bullet.deploy()

                this.ammunitionCount--
            },
            1.5 * 1000
        )
    }

    destroy() {
        container.removeChild(this.node)
    }
}

const EVENTS = {
    POSITION: 'position',
    MOVEMENT: 'movement',
    ENEMY: 'enemy',
    ATACK: 'atack',
    LEVEL: 'level',
    LEVELS: 'levels'
}

const MOVEMENTS = {
    ArrowRight: 'right',
    ArrowLeft: 'left'
}

socket.on(
    EVENTS.POSITION,
    position => player.style.setProperty(
        'left',
        `${position}px`
    )
)

socket.on(
    EVENTS.ENEMY,
    position => {
        const enemy = new Enemy({ position })

        enemy.deploy()
    }
)

socket.on(
    EVENTS.ATACK,
    damage => {
        console.log('Golpe recibido')

        player.classList.add('damage')

        setTimeout(
            () => player.classList.remove('damage'),
            250
        )
    }
)

socket.on(
    EVENTS.LEVEL,
    code => {
        level.querySelector('.title').textContent = `Has llegado al nivel: ${code}!`
        level.style.setProperty(
            'display',
            'grid'
        )

        setTimeout(
            () => level.style.setProperty(
                'display',
                'none'
            ),
            5000
        )
    }
)

socket.on(
    EVENTS.LEVELS,
    levels => console.log('Niveles terminados: ', levels)
)

window.addEventListener(
    'keydown',
    event => {
        MOVEMENTS[event.code] 
        && socket.emit(
            EVENTS.MOVEMENT,
            MOVEMENTS[event.code]
        )
    }
)