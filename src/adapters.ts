const getAdaptedData = (controllerData: any) => {
    const data = String(controllerData)

    const [
        key,
        value
    ] = data.split('-')

    return {
        key,
        value
    }
}

export { getAdaptedData }