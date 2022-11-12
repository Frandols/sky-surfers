const getAdaptedData = (socketData: string) => {
    const [
        key,
        value
    ] = socketData.split('-')

    return {
        key,
        value
    }
}

export { getAdaptedData }