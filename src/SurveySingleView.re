open TW;

[@react.component]
let make = (~id) => {
  let (data, _) = SurveySingleQuery.use(~id);
  let (edit, editSurvey) = SurveyMutation.useEdit();
  let (questions: array(Survey.Question.t), setQuestions) =
    React.useState(() => [||]);
  let (name, setName) = React.useState(() => "");
  let (desc, setDesc) = React.useState(() => "");

  let notification = Notification.use();

  React.useEffect1(
    () => {
      switch (data.data) {
      | Some(data) =>
        let survey = data##form;
        setName(_ => survey##title);
        setDesc(_ => survey##content->Belt.Option.getWithDefault(""));
        setQuestions(_ => SurveyForm.fromQuestions(survey##questions));
      | None => ()
      };
      None;
    },
    [|data|],
  );

  <Layout>
    <div className={[Display(Flex), JustifyContent(JustifyBetween)]->make}>
      <Text className=[FontSize(Text2xl), Margin(Mr4)]>
        {j|Edycja ankiety - $id|j}
      </Text>
      <Button
        onClick={_ =>
          editSurvey(
            ~id,
            ~formInput={
              "title": name,
              "content": desc,
              "questions": SurveyForm.mapQuestions(questions),
              "parentId": None,
            },
            (),
          )
          |> Js.Promise.then_(_ => {
               notification.show(
                 `success,
                 {j|Operacja zakończona pomyślnie!|j},
               );

               Js.Promise.resolve();
             })
          |> ignore
        }>
        <Text color=`white> {j|Zapisz zmiany|j} </Text>
      </Button>
    </div>
    {switch (data.response) {
     | Data(_) =>
       <SurveyForm
         name
         setName
         desc
         setDesc
         fetching={edit.fetching}
         questions
         setQuestions
       />

     | Error(_) =>
       <Text>
         {j|Wystąpił błąd podczas łączenia się z serwerem|j}
       </Text>
     | Fetching => <Text> {j|Trwa wczytywanie danych|j} </Text>
     | NotFound => <Text> {j|Rekord o podanym ID nie istnieje|j} </Text>
     }}
  </Layout>;
};